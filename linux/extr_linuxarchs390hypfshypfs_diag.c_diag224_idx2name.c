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
 int DIAG204_CPU_NAME_LEN ; 
 scalar_t__ diag224_cpu_names ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  strim (char*) ; 

__attribute__((used)) static int diag224_idx2name(int index, char *name)
{
	memcpy(name, diag224_cpu_names + ((index + 1) * DIAG204_CPU_NAME_LEN),
	       DIAG204_CPU_NAME_LEN);
	name[DIAG204_CPU_NAME_LEN] = 0;
	strim(name);
	return 0;
}