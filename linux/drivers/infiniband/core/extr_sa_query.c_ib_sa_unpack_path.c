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
struct sa_path_rec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_unpack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct sa_path_rec*) ; 
 int /*<<< orphan*/  path_rec_table ; 

void ib_sa_unpack_path(void *attribute, struct sa_path_rec *rec)
{
	ib_unpack(path_rec_table, ARRAY_SIZE(path_rec_table), attribute, rec);
}