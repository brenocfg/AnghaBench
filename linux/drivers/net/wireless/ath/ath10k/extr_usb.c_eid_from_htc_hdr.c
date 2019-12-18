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
struct ath10k_htc_hdr {int /*<<< orphan*/  eid; } ;
typedef  enum ath10k_htc_ep_id { ____Placeholder_ath10k_htc_ep_id } ath10k_htc_ep_id ;

/* Variables and functions */

__attribute__((used)) static inline enum ath10k_htc_ep_id
eid_from_htc_hdr(struct ath10k_htc_hdr *htc_hdr)
{
	return (enum ath10k_htc_ep_id)htc_hdr->eid;
}