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
struct dc_plane_address {int dummy; } ;
struct mem_input {struct dc_plane_address request_address; } ;
struct dce_mem_input {int dummy; } ;

/* Variables and functions */
 struct dce_mem_input* TO_DCE_MEM_INPUT (struct mem_input*) ; 
 int /*<<< orphan*/  program_addr (struct dce_mem_input*,struct dc_plane_address const*) ; 
 int /*<<< orphan*/  set_flip_control (struct dce_mem_input*,int) ; 

bool dce_mem_input_v_program_surface_flip_and_addr(
	struct mem_input *mem_input,
	const struct dc_plane_address *address,
	bool flip_immediate)
{
	struct dce_mem_input *mem_input110 = TO_DCE_MEM_INPUT(mem_input);

	set_flip_control(mem_input110, flip_immediate);
	program_addr(mem_input110,
		address);

	mem_input->request_address = *address;

	return true;
}