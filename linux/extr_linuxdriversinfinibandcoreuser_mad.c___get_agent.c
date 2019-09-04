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
struct ib_umad_file {struct ib_mad_agent** agent; scalar_t__ agents_dead; } ;
struct ib_mad_agent {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct ib_mad_agent *__get_agent(struct ib_umad_file *file, int id)
{
	return file->agents_dead ? NULL : file->agent[id];
}