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
struct cfg80211_beacon_data {int /*<<< orphan*/  assocresp_ies_len; int /*<<< orphan*/  assocresp_ies; int /*<<< orphan*/  proberesp_ies_len; int /*<<< orphan*/  proberesp_ies; int /*<<< orphan*/  probe_resp_len; int /*<<< orphan*/  probe_resp; int /*<<< orphan*/  beacon_ies_len; int /*<<< orphan*/  beacon_ies; int /*<<< orphan*/  tail_len; int /*<<< orphan*/  tail; int /*<<< orphan*/  head_len; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  wil_hex_dump_misc (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wil_print_bcon_data(struct cfg80211_beacon_data *b)
{
	wil_hex_dump_misc("head     ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->head, b->head_len, true);
	wil_hex_dump_misc("tail     ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->tail, b->tail_len, true);
	wil_hex_dump_misc("BCON IE  ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->beacon_ies, b->beacon_ies_len, true);
	wil_hex_dump_misc("PROBE    ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->probe_resp, b->probe_resp_len, true);
	wil_hex_dump_misc("PROBE IE ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->proberesp_ies, b->proberesp_ies_len, true);
	wil_hex_dump_misc("ASSOC IE ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->assocresp_ies, b->assocresp_ies_len, true);
}