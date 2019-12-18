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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  swreg ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NN_REG_VAL ; 
 int /*<<< orphan*/  swreg_raw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 swreg_value(swreg reg)
{
	return FIELD_GET(NN_REG_VAL, swreg_raw(reg));
}