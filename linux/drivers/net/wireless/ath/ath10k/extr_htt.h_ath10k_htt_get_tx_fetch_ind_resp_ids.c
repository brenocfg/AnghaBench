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
struct htt_tx_fetch_ind {int /*<<< orphan*/  num_records; int /*<<< orphan*/ * records; } ;

/* Variables and functions */
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *
ath10k_htt_get_tx_fetch_ind_resp_ids(struct htt_tx_fetch_ind *ind)
{
	return (void *)&ind->records[le16_to_cpu(ind->num_records)];
}