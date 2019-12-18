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
struct ath10k_htc_hdr {scalar_t__ trailer_len; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 scalar_t__ __le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_trailer_only_msg(struct ath10k_htc_hdr *htc_hdr)
{
	return __le16_to_cpu(htc_hdr->len) == htc_hdr->trailer_len;
}