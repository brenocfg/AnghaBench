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
struct bio {int /*<<< orphan*/  bi_opf; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ bio_op (struct bio*) ; 
 scalar_t__ op_is_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool discard_or_flush(struct bio *bio)
{
	return bio_op(bio) == REQ_OP_DISCARD || op_is_flush(bio->bi_opf);
}