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
struct nicpf {int num_sqs_en; int* sqs_used; int num_vf_en; } ;

/* Variables and functions */

__attribute__((used)) static int nic_nxt_avail_sqs(struct nicpf *nic)
{
	int sqs;

	for (sqs = 0; sqs < nic->num_sqs_en; sqs++) {
		if (!nic->sqs_used[sqs])
			nic->sqs_used[sqs] = true;
		else
			continue;
		return sqs + nic->num_vf_en;
	}
	return -1;
}