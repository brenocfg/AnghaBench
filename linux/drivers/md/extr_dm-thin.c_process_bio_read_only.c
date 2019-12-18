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
struct thin_c {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __process_bio_read_only (struct thin_c*,struct bio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_bio_read_only(struct thin_c *tc, struct bio *bio)
{
	__process_bio_read_only(tc, bio, NULL);
}