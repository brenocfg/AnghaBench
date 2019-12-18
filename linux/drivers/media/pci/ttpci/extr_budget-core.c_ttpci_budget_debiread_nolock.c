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
typedef  int u32 ;
struct saa7146_dev {int dummy; } ;
struct budget {struct saa7146_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBI_AD ; 
 int /*<<< orphan*/  DEBI_COMMAND ; 
 int /*<<< orphan*/  DEBI_CONFIG ; 
 int /*<<< orphan*/  DEBI_PAGE ; 
 int /*<<< orphan*/  MC2 ; 
 int saa7146_read (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int saa7146_wait_for_debi_done (struct saa7146_dev*,int) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ttpci_budget_debiread_nolock(struct budget *budget, u32 config,
		int addr, int count, int nobusyloop)
{
	struct saa7146_dev *saa = budget->dev;
	int result;

	result = saa7146_wait_for_debi_done(saa, nobusyloop);
	if (result < 0)
		return result;

	saa7146_write(saa, DEBI_COMMAND, (count << 17) | 0x10000 | (addr & 0xffff));
	saa7146_write(saa, DEBI_CONFIG, config);
	saa7146_write(saa, DEBI_PAGE, 0);
	saa7146_write(saa, MC2, (2 << 16) | 2);

	result = saa7146_wait_for_debi_done(saa, nobusyloop);
	if (result < 0)
		return result;

	result = saa7146_read(saa, DEBI_AD);
	result &= (0xffffffffUL >> ((4 - count) * 8));
	return result;
}