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
struct bsg_job {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 

int zfcp_fc_timeout_bsg_job(struct bsg_job *job)
{
	/* hardware tracks timeout, reset bsg timeout to not interfere */
	return -EAGAIN;
}