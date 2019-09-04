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
typedef  int /*<<< orphan*/  u32 ;
struct slic_upr {scalar_t__ type; int /*<<< orphan*/  paddr; } ;
struct slic_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIC_REG_LSTAT ; 
 int /*<<< orphan*/  SLIC_REG_RCONFIG ; 
 scalar_t__ SLIC_UPR_CONFIG ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slic_flush_write (struct slic_device*) ; 
 int /*<<< orphan*/  slic_write (struct slic_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slic_start_upr(struct slic_device *sdev, struct slic_upr *upr)
{
	u32 reg;

	reg = (upr->type == SLIC_UPR_CONFIG) ? SLIC_REG_RCONFIG :
					       SLIC_REG_LSTAT;
	slic_write(sdev, reg, lower_32_bits(upr->paddr));
	slic_flush_write(sdev);
}