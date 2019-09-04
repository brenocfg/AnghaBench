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
struct dm_integrity_c {int /*<<< orphan*/  failed; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm_integrity_failed(struct dm_integrity_c *ic)
{
	return READ_ONCE(ic->failed);
}