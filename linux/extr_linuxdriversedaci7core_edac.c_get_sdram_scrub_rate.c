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
typedef  unsigned long long u32 ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {struct i7core_pvt* pvt_info; } ;
struct i7core_pvt {unsigned long long dclk_freq; struct pci_dev** pci_mcr; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MC_SCRUB_CONTROL ; 
 unsigned long long SCRUBINTERVAL_MASK ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,unsigned long long*) ; 

__attribute__((used)) static int get_sdram_scrub_rate(struct mem_ctl_info *mci)
{
	struct i7core_pvt *pvt = mci->pvt_info;
	struct pci_dev *pdev;
	const u32 cache_line_size = 64;
	const u32 freq_dclk_mhz = pvt->dclk_freq;
	unsigned long long scrub_rate;
	u32 scrubval;

	/* Get data from the MC register, function 2 */
	pdev = pvt->pci_mcr[2];
	if (!pdev)
		return -ENODEV;

	/* Get current scrub control data */
	pci_read_config_dword(pdev, MC_SCRUB_CONTROL, &scrubval);

	/* Mask highest 8-bits to 0 */
	scrubval &=  SCRUBINTERVAL_MASK;
	if (!scrubval)
		return 0;

	/* Calculate scrub rate value into byte/sec bandwidth */
	scrub_rate =  (unsigned long long)freq_dclk_mhz *
		1000000 * cache_line_size;
	do_div(scrub_rate, scrubval);
	return (int)scrub_rate;
}