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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  atom_exec_context ;

/* Variables and functions */
 int** atom_dst_to_src ; 
 int /*<<< orphan*/  atom_skip_src_int (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static void atom_skip_dst(atom_exec_context *ctx, int arg, uint8_t attr, int *ptr)
{
	atom_skip_src_int(ctx,
			  arg | atom_dst_to_src[(attr >> 3) & 7][(attr >> 6) &
								 3] << 3, ptr);
}