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
struct bsd_db {int /*<<< orphan*/  checkpoint; scalar_t__ ratio; scalar_t__ incomp_count; scalar_t__ in_count; scalar_t__ bytes_out; int /*<<< orphan*/  n_bits; scalar_t__ max_ent; int /*<<< orphan*/  clear_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSD_INIT_BITS ; 
 int /*<<< orphan*/  CHECK_GAP ; 
 scalar_t__ FIRST ; 

__attribute__((used)) static void bsd_clear(struct bsd_db *db)
{
	db->clear_count++;
	db->max_ent      = FIRST - 1;
	db->n_bits       = BSD_INIT_BITS;
	db->bytes_out    = 0;
	db->in_count     = 0;
	db->incomp_count = 0;
	db->ratio	     = 0;
	db->checkpoint   = CHECK_GAP;
}