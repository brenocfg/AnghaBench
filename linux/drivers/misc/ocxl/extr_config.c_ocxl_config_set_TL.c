#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  long u32 ;
struct pci_dev {int /*<<< orphan*/  devfn; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 long GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OCXL_DVSEC_TL_BACKOFF_TIMERS ; 
 scalar_t__ OCXL_DVSEC_TL_RECV_CAP ; 
 scalar_t__ OCXL_DVSEC_TL_RECV_RATE ; 
 scalar_t__ OCXL_DVSEC_TL_SEND_CAP ; 
 scalar_t__ OCXL_DVSEC_TL_SEND_RATE ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PNV_OCXL_TL_RATE_BUF_SIZE ; 
 int /*<<< orphan*/  __pa (char*) ; 
 long be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (long) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,long*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,long) ; 
 int pnv_ocxl_get_tl_cap (struct pci_dev*,long*,char*,int) ; 
 int pnv_ocxl_set_tl_conf (struct pci_dev*,long,int /*<<< orphan*/ ,int) ; 

int ocxl_config_set_TL(struct pci_dev *dev, int tl_dvsec)
{
	u32 val;
	__be32 *be32ptr;
	u8 timers;
	int i, rc;
	long recv_cap;
	char *recv_rate;

	/*
	 * Skip on function != 0, as the TL can only be defined on 0
	 */
	if (PCI_FUNC(dev->devfn) != 0)
		return 0;

	recv_rate = kzalloc(PNV_OCXL_TL_RATE_BUF_SIZE, GFP_KERNEL);
	if (!recv_rate)
		return -ENOMEM;
	/*
	 * The spec defines 64 templates for messages in the
	 * Transaction Layer (TL).
	 *
	 * The host and device each support a subset, so we need to
	 * configure the transmitters on each side to send only
	 * templates the receiver understands, at a rate the receiver
	 * can process.  Per the spec, template 0 must be supported by
	 * everybody. That's the template which has been used by the
	 * host and device so far.
	 *
	 * The sending rate limit must be set before the template is
	 * enabled.
	 */

	/*
	 * Device -> host
	 */
	rc = pnv_ocxl_get_tl_cap(dev, &recv_cap, recv_rate,
				PNV_OCXL_TL_RATE_BUF_SIZE);
	if (rc)
		goto out;

	for (i = 0; i < PNV_OCXL_TL_RATE_BUF_SIZE; i += 4) {
		be32ptr = (__be32 *) &recv_rate[i];
		pci_write_config_dword(dev,
				tl_dvsec + OCXL_DVSEC_TL_SEND_RATE + i,
				be32_to_cpu(*be32ptr));
	}
	val = recv_cap >> 32;
	pci_write_config_dword(dev, tl_dvsec + OCXL_DVSEC_TL_SEND_CAP, val);
	val = recv_cap & GENMASK(31, 0);
	pci_write_config_dword(dev, tl_dvsec + OCXL_DVSEC_TL_SEND_CAP + 4, val);

	/*
	 * Host -> device
	 */
	for (i = 0; i < PNV_OCXL_TL_RATE_BUF_SIZE; i += 4) {
		pci_read_config_dword(dev,
				tl_dvsec + OCXL_DVSEC_TL_RECV_RATE + i,
				&val);
		be32ptr = (__be32 *) &recv_rate[i];
		*be32ptr = cpu_to_be32(val);
	}
	pci_read_config_dword(dev, tl_dvsec + OCXL_DVSEC_TL_RECV_CAP, &val);
	recv_cap = (long) val << 32;
	pci_read_config_dword(dev, tl_dvsec + OCXL_DVSEC_TL_RECV_CAP + 4, &val);
	recv_cap |= val;

	rc = pnv_ocxl_set_tl_conf(dev, recv_cap, __pa(recv_rate),
				PNV_OCXL_TL_RATE_BUF_SIZE);
	if (rc)
		goto out;

	/*
	 * Opencapi commands needing to be retried are classified per
	 * the TL in 2 groups: short and long commands.
	 *
	 * The short back off timer it not used for now. It will be
	 * for opencapi 4.0.
	 *
	 * The long back off timer is typically used when an AFU hits
	 * a page fault but the NPU is already processing one. So the
	 * AFU needs to wait before it can resubmit. Having a value
	 * too low doesn't break anything, but can generate extra
	 * traffic on the link.
	 * We set it to 1.6 us for now. It's shorter than, but in the
	 * same order of magnitude as the time spent to process a page
	 * fault.
	 */
	timers = 0x2 << 4; /* long timer = 1.6 us */
	pci_write_config_byte(dev, tl_dvsec + OCXL_DVSEC_TL_BACKOFF_TIMERS,
			timers);

	rc = 0;
out:
	kfree(recv_rate);
	return rc;
}