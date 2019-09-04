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
typedef  int /*<<< orphan*/  u8 ;
struct fintek_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCR_LOGICAL_DEV_NO ; 
 int /*<<< orphan*/  fintek_cr_write (struct fintek_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fintek_select_logical_dev(struct fintek_dev *fintek, u8 ldev)
{
	fintek_cr_write(fintek, ldev, GCR_LOGICAL_DEV_NO);
}