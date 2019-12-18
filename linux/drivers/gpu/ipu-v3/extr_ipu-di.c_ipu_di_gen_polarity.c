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

/* Variables and functions */
 int /*<<< orphan*/  DI_GEN_POLARITY_1 ; 
 int /*<<< orphan*/  DI_GEN_POLARITY_2 ; 
 int /*<<< orphan*/  DI_GEN_POLARITY_3 ; 
 int /*<<< orphan*/  DI_GEN_POLARITY_4 ; 
 int /*<<< orphan*/  DI_GEN_POLARITY_5 ; 
 int /*<<< orphan*/  DI_GEN_POLARITY_6 ; 
 int /*<<< orphan*/  DI_GEN_POLARITY_7 ; 
 int /*<<< orphan*/  DI_GEN_POLARITY_8 ; 

__attribute__((used)) static u32 ipu_di_gen_polarity(int pin)
{
	switch (pin) {
	case 1:
		return DI_GEN_POLARITY_1;
	case 2:
		return DI_GEN_POLARITY_2;
	case 3:
		return DI_GEN_POLARITY_3;
	case 4:
		return DI_GEN_POLARITY_4;
	case 5:
		return DI_GEN_POLARITY_5;
	case 6:
		return DI_GEN_POLARITY_6;
	case 7:
		return DI_GEN_POLARITY_7;
	case 8:
		return DI_GEN_POLARITY_8;
	}
	return 0;
}