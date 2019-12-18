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
struct r1conf {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  _allow_barrier (struct r1conf*,int) ; 
 int sector_to_idx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void allow_barrier(struct r1conf *conf, sector_t sector_nr)
{
	int idx = sector_to_idx(sector_nr);

	_allow_barrier(conf, idx);
}