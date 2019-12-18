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
struct debug_drvdata {int edprsr; } ;

/* Variables and functions */
 int EDPRSR_DLK ; 
 int EDPRSR_PU ; 

__attribute__((used)) static bool debug_access_permitted(struct debug_drvdata *drvdata)
{
	/* CPU is powered off */
	if (!(drvdata->edprsr & EDPRSR_PU))
		return false;

	/* The OS Double Lock is locked */
	if (drvdata->edprsr & EDPRSR_DLK)
		return false;

	return true;
}