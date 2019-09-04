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
 int /*<<< orphan*/  CEDE_LATENCY_PARAM_MAX_LENGTH ; 
 int /*<<< orphan*/  CEDE_LATENCY_TOKEN ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cede_parameters ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_token (char*) ; 

__attribute__((used)) static int parse_cede_parameters(void)
{
	memset(cede_parameters, 0, CEDE_LATENCY_PARAM_MAX_LENGTH);
	return rtas_call(rtas_token("ibm,get-system-parameter"), 3, 1,
			 NULL,
			 CEDE_LATENCY_TOKEN,
			 __pa(cede_parameters),
			 CEDE_LATENCY_PARAM_MAX_LENGTH);
}