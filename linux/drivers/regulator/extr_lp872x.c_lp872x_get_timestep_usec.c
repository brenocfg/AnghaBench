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
struct lp872x {int chipid; } ;
typedef  enum lp872x_id { ____Placeholder_lp872x_id } lp872x_id ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  LP8720 129 
 int LP8720_TIMESTEP_M ; 
 int LP8720_TIMESTEP_S ; 
#define  LP8725 128 
 int LP8725_TIMESTEP_M ; 
 int LP8725_TIMESTEP_S ; 
 int /*<<< orphan*/  LP872X_GENERAL_CFG ; 
 int lp872x_read_byte (struct lp872x*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lp872x_get_timestep_usec(struct lp872x *lp)
{
	enum lp872x_id chip = lp->chipid;
	u8 val, mask, shift;
	int *time_usec, size, ret;
	int lp8720_time_usec[] = { 25, 50 };
	int lp8725_time_usec[] = { 32, 64, 128, 256 };

	switch (chip) {
	case LP8720:
		mask = LP8720_TIMESTEP_M;
		shift = LP8720_TIMESTEP_S;
		time_usec = &lp8720_time_usec[0];
		size = ARRAY_SIZE(lp8720_time_usec);
		break;
	case LP8725:
		mask = LP8725_TIMESTEP_M;
		shift = LP8725_TIMESTEP_S;
		time_usec = &lp8725_time_usec[0];
		size = ARRAY_SIZE(lp8725_time_usec);
		break;
	default:
		return -EINVAL;
	}

	ret = lp872x_read_byte(lp, LP872X_GENERAL_CFG, &val);
	if (ret)
		return ret;

	val = (val & mask) >> shift;
	if (val >= size)
		return -EINVAL;

	return *(time_usec + val);
}