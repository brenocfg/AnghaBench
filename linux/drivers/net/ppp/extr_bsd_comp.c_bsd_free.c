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
struct bsd_db {int /*<<< orphan*/ * lens; int /*<<< orphan*/ * dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct bsd_db*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bsd_free (void *state)
{
	struct bsd_db *db = state;

	if (!db)
		return;

/*
 * Release the dictionary
 */
	vfree(db->dict);
	db->dict = NULL;
/*
 * Release the string buffer
 */
	vfree(db->lens);
	db->lens = NULL;
/*
 * Finally release the structure itself.
 */
	kfree(db);
}