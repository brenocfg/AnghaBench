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
struct stv {int dummy; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  scrambling_sequence_index; int /*<<< orphan*/  stream_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_isi (struct stv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pls (struct stv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_stream_modes(struct stv *state,
			     struct dtv_frontend_properties *p)
{
	set_isi(state, p->stream_id);
	set_pls(state, p->scrambling_sequence_index);
}