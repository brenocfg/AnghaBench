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
struct tda8083_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tda8083_readregs (struct tda8083_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline u8 tda8083_readreg (struct tda8083_state* state, u8 reg)
{
	u8 val;

	tda8083_readregs (state, reg, &val, 1);

	return val;
}