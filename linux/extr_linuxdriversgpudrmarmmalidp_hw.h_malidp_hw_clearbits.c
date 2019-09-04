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
struct malidp_hw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  malidp_hw_read (struct malidp_hw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_write (struct malidp_hw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void malidp_hw_clearbits(struct malidp_hw_device *hwdev,
				       u32 mask, u32 reg)
{
	u32 data = malidp_hw_read(hwdev, reg);

	data &= ~mask;
	malidp_hw_write(hwdev, data, reg);
}