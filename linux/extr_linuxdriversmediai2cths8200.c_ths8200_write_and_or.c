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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int ths8200_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ths8200_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
ths8200_write_and_or(struct v4l2_subdev *sd, u8 reg,
		     uint8_t clr_mask, uint8_t val_mask)
{
	ths8200_write(sd, reg, (ths8200_read(sd, reg) & clr_mask) | val_mask);
}