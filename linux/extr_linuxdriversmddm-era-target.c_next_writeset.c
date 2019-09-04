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
struct writeset {int dummy; } ;
struct era_metadata {struct writeset* writesets; struct writeset* current_writeset; } ;

/* Variables and functions */

__attribute__((used)) static struct writeset *next_writeset(struct era_metadata *md)
{
	return (md->current_writeset == &md->writesets[0]) ?
		&md->writesets[1] : &md->writesets[0];
}