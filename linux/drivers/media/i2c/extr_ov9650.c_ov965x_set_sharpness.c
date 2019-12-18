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
struct ov965x {int dummy; } ;

/* Variables and functions */
 int COM14_EDGE_EN ; 
 int COM14_EEF_X2 ; 
 int EDGE_FACTOR_MASK ; 
 int /*<<< orphan*/  REG_COM14 ; 
 int /*<<< orphan*/  REG_EDGE ; 
 int ov965x_read (struct ov965x*,int /*<<< orphan*/ ,int*) ; 
 int ov965x_write (struct ov965x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov965x_set_sharpness(struct ov965x *ov965x, unsigned int value)
{
	u8 com14, edge;
	int ret;

	ret = ov965x_read(ov965x, REG_COM14, &com14);
	if (ret < 0)
		return ret;
	ret = ov965x_read(ov965x, REG_EDGE, &edge);
	if (ret < 0)
		return ret;
	com14 = value ? com14 | COM14_EDGE_EN : com14 & ~COM14_EDGE_EN;
	value--;
	if (value > 0x0f) {
		com14 |= COM14_EEF_X2;
		value >>= 1;
	} else {
		com14 &= ~COM14_EEF_X2;
	}
	ret = ov965x_write(ov965x, REG_COM14, com14);
	if (ret < 0)
		return ret;

	edge &= ~EDGE_FACTOR_MASK;
	edge |= ((u8)value & 0x0f);

	return ov965x_write(ov965x, REG_EDGE, edge);
}