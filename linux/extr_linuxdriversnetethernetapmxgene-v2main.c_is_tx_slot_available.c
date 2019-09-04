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
struct xge_raw_desc {int /*<<< orphan*/  m0; } ;

/* Variables and functions */
 int /*<<< orphan*/  E ; 
 scalar_t__ GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKT_SIZE ; 
 scalar_t__ SLOT_EMPTY ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_tx_slot_available(struct xge_raw_desc *raw_desc)
{
	if (GET_BITS(E, le64_to_cpu(raw_desc->m0)) &&
	    (GET_BITS(PKT_SIZE, le64_to_cpu(raw_desc->m0)) == SLOT_EMPTY))
		return true;

	return false;
}