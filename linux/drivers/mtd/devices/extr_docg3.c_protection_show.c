#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {scalar_t__ private; } ;
struct docg3 {TYPE_1__* cascade; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOC_DPS0_ADDRHIGH ; 
 int /*<<< orphan*/  DOC_DPS0_ADDRLOW ; 
 int /*<<< orphan*/  DOC_DPS0_STATUS ; 
 int /*<<< orphan*/  DOC_DPS1_ADDRHIGH ; 
 int /*<<< orphan*/  DOC_DPS1_ADDRLOW ; 
 int /*<<< orphan*/  DOC_DPS1_STATUS ; 
 int DOC_DPS_HW_LOCK_ENABLED ; 
 int DOC_DPS_KEY_OK ; 
 int DOC_DPS_OTP_PROTECTED ; 
 int DOC_DPS_READ_PROTECTED ; 
 int DOC_DPS_WRITE_PROTECTED ; 
 int /*<<< orphan*/  DOC_PROTECTION ; 
 int DOC_PROTECT_CUSTOMER_OTP_LOCK ; 
 int DOC_PROTECT_FOUNDRY_OTP_LOCK ; 
 int DOC_PROTECT_IPL_DOWNLOAD_LOCK ; 
 int DOC_PROTECT_LOCK_INPUT ; 
 int DOC_PROTECT_PROTECTION_ENABLED ; 
 int DOC_PROTECT_PROTECTION_ERROR ; 
 int DOC_PROTECT_STICKY_LOCK ; 
 int doc_register_readb (struct docg3*,int /*<<< orphan*/ ) ; 
 int doc_register_readw (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int protection_show(struct seq_file *s, void *p)
{
	struct docg3 *docg3 = (struct docg3 *)s->private;
	int protect, dps0, dps0_low, dps0_high, dps1, dps1_low, dps1_high;

	mutex_lock(&docg3->cascade->lock);
	protect = doc_register_readb(docg3, DOC_PROTECTION);
	dps0 = doc_register_readb(docg3, DOC_DPS0_STATUS);
	dps0_low = doc_register_readw(docg3, DOC_DPS0_ADDRLOW);
	dps0_high = doc_register_readw(docg3, DOC_DPS0_ADDRHIGH);
	dps1 = doc_register_readb(docg3, DOC_DPS1_STATUS);
	dps1_low = doc_register_readw(docg3, DOC_DPS1_ADDRLOW);
	dps1_high = doc_register_readw(docg3, DOC_DPS1_ADDRHIGH);
	mutex_unlock(&docg3->cascade->lock);

	seq_printf(s, "Protection = 0x%02x (", protect);
	if (protect & DOC_PROTECT_FOUNDRY_OTP_LOCK)
		seq_puts(s, "FOUNDRY_OTP_LOCK,");
	if (protect & DOC_PROTECT_CUSTOMER_OTP_LOCK)
		seq_puts(s, "CUSTOMER_OTP_LOCK,");
	if (protect & DOC_PROTECT_LOCK_INPUT)
		seq_puts(s, "LOCK_INPUT,");
	if (protect & DOC_PROTECT_STICKY_LOCK)
		seq_puts(s, "STICKY_LOCK,");
	if (protect & DOC_PROTECT_PROTECTION_ENABLED)
		seq_puts(s, "PROTECTION ON,");
	if (protect & DOC_PROTECT_IPL_DOWNLOAD_LOCK)
		seq_puts(s, "IPL_DOWNLOAD_LOCK,");
	if (protect & DOC_PROTECT_PROTECTION_ERROR)
		seq_puts(s, "PROTECT_ERR,");
	else
		seq_puts(s, "NO_PROTECT_ERR");
	seq_puts(s, ")\n");

	seq_printf(s, "DPS0 = 0x%02x : Protected area [0x%x - 0x%x] : OTP=%d, READ=%d, WRITE=%d, HW_LOCK=%d, KEY_OK=%d\n",
		   dps0, dps0_low, dps0_high,
		   !!(dps0 & DOC_DPS_OTP_PROTECTED),
		   !!(dps0 & DOC_DPS_READ_PROTECTED),
		   !!(dps0 & DOC_DPS_WRITE_PROTECTED),
		   !!(dps0 & DOC_DPS_HW_LOCK_ENABLED),
		   !!(dps0 & DOC_DPS_KEY_OK));
	seq_printf(s, "DPS1 = 0x%02x : Protected area [0x%x - 0x%x] : OTP=%d, READ=%d, WRITE=%d, HW_LOCK=%d, KEY_OK=%d\n",
		   dps1, dps1_low, dps1_high,
		   !!(dps1 & DOC_DPS_OTP_PROTECTED),
		   !!(dps1 & DOC_DPS_READ_PROTECTED),
		   !!(dps1 & DOC_DPS_WRITE_PROTECTED),
		   !!(dps1 & DOC_DPS_HW_LOCK_ENABLED),
		   !!(dps1 & DOC_DPS_KEY_OK));
	return 0;
}