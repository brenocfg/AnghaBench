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
 int /*<<< orphan*/  UDS_MAX_FACTOR ; 
 int /*<<< orphan*/  UDS_MAX_SIZE ; 
 int /*<<< orphan*/  UDS_MIN_FACTOR ; 
 int /*<<< orphan*/  UDS_MIN_SIZE ; 
 unsigned int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uds_output_size (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uds_output_limits(unsigned int input,
			      unsigned int *minimum, unsigned int *maximum)
{
	*minimum = max(uds_output_size(input, UDS_MAX_FACTOR), UDS_MIN_SIZE);
	*maximum = min(uds_output_size(input, UDS_MIN_FACTOR), UDS_MAX_SIZE);
}