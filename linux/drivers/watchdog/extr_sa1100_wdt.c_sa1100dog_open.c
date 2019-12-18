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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  OIER ; 
 int OIER_E3 ; 
 int /*<<< orphan*/  OSCR ; 
 int /*<<< orphan*/  OSMR3 ; 
 int /*<<< orphan*/  OSSR ; 
 int OSSR_M3 ; 
 int /*<<< orphan*/  OWER ; 
 int OWER_WME ; 
 int pre_margin ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1100wdt_users ; 
 int stream_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sa1100dog_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(1, &sa1100wdt_users))
		return -EBUSY;

	/* Activate SA1100 Watchdog timer */
	writel_relaxed(readl_relaxed(OSCR) + pre_margin, OSMR3);
	writel_relaxed(OSSR_M3, OSSR);
	writel_relaxed(OWER_WME, OWER);
	writel_relaxed(readl_relaxed(OIER) | OIER_E3, OIER);
	return stream_open(inode, file);
}