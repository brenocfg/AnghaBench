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
struct arm_smccc_res {int a0; } ;

/* Variables and functions */
#define  SDEI_DENIED 132 
#define  SDEI_INVALID_PARAMETERS 131 
#define  SDEI_NOT_SUPPORTED 130 
#define  SDEI_OUT_OF_RESOURCE 129 
#define  SDEI_PENDING 128 

__attribute__((used)) static int sdei_is_err(struct arm_smccc_res *res)
{
	switch (res->a0) {
	case SDEI_NOT_SUPPORTED:
	case SDEI_INVALID_PARAMETERS:
	case SDEI_DENIED:
	case SDEI_PENDING:
	case SDEI_OUT_OF_RESOURCE:
		return true;
	}

	return false;
}