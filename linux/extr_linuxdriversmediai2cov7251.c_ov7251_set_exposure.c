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
typedef  int /*<<< orphan*/  u16 ;
struct ov7251 {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  OV7251_AEC_EXPO_0 ; 
 int ov7251_write_seq_regs (struct ov7251*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ov7251_set_exposure(struct ov7251 *ov7251, s32 exposure)
{
	u16 reg;
	u8 val[3];

	reg = OV7251_AEC_EXPO_0;
	val[0] = (exposure & 0xf000) >> 12; /* goes to OV7251_AEC_EXPO_0 */
	val[1] = (exposure & 0x0ff0) >> 4;  /* goes to OV7251_AEC_EXPO_1 */
	val[2] = (exposure & 0x000f) << 4;  /* goes to OV7251_AEC_EXPO_2 */

	return ov7251_write_seq_regs(ov7251, reg, val, 3);
}