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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage(void)
{
	printf("\nUsage: ./firmware <gb-fw-mgmt-X (default: gb-fw-mgmt-0)> <interface: 0, backend: 1 (default: 0)> <firmware-tag> (default: \"s3f\"/\"bf_01\") <timeout (default: 10000 ms)>\n");
}