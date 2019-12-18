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
struct compstat {int /*<<< orphan*/  bytes_out; int /*<<< orphan*/  in_count; int /*<<< orphan*/  inc_packets; int /*<<< orphan*/  inc_bytes; int /*<<< orphan*/  comp_packets; int /*<<< orphan*/  comp_bytes; int /*<<< orphan*/  unc_packets; int /*<<< orphan*/  unc_bytes; } ;
struct bsd_db {int /*<<< orphan*/  bytes_out; int /*<<< orphan*/  in_count; int /*<<< orphan*/  incomp_count; int /*<<< orphan*/  incomp_bytes; int /*<<< orphan*/  comp_count; int /*<<< orphan*/  comp_bytes; int /*<<< orphan*/  uncomp_count; int /*<<< orphan*/  uncomp_bytes; } ;

/* Variables and functions */

__attribute__((used)) static void bsd_comp_stats (void *state, struct compstat *stats)
  {
    struct bsd_db *db = (struct bsd_db *) state;

    stats->unc_bytes    = db->uncomp_bytes;
    stats->unc_packets  = db->uncomp_count;
    stats->comp_bytes   = db->comp_bytes;
    stats->comp_packets = db->comp_count;
    stats->inc_bytes    = db->incomp_bytes;
    stats->inc_packets  = db->incomp_count;
    stats->in_count     = db->in_count;
    stats->bytes_out    = db->bytes_out;
  }