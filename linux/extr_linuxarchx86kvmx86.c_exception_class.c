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

/* Variables and functions */
#define  DE_VECTOR 133 
 int EXCPT_BENIGN ; 
 int EXCPT_CONTRIBUTORY ; 
 int EXCPT_PF ; 
#define  GP_VECTOR 132 
#define  NP_VECTOR 131 
#define  PF_VECTOR 130 
#define  SS_VECTOR 129 
#define  TS_VECTOR 128 

__attribute__((used)) static int exception_class(int vector)
{
	switch (vector) {
	case PF_VECTOR:
		return EXCPT_PF;
	case DE_VECTOR:
	case TS_VECTOR:
	case NP_VECTOR:
	case SS_VECTOR:
	case GP_VECTOR:
		return EXCPT_CONTRIBUTORY;
	default:
		break;
	}
	return EXCPT_BENIGN;
}