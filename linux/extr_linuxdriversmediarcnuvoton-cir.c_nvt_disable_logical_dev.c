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
struct nvt_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_LOGICAL_DEV_EN ; 
 int /*<<< orphan*/  LOGICAL_DEV_DISABLE ; 
 int /*<<< orphan*/  nvt_cr_write (struct nvt_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_efm_disable (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_efm_enable (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_select_logical_dev (struct nvt_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nvt_disable_logical_dev(struct nvt_dev *nvt, u8 ldev)
{
	nvt_efm_enable(nvt);
	nvt_select_logical_dev(nvt, ldev);
	nvt_cr_write(nvt, LOGICAL_DEV_DISABLE, CR_LOGICAL_DEV_EN);
	nvt_efm_disable(nvt);
}