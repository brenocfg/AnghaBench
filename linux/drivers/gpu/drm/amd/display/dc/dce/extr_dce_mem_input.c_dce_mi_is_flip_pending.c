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
typedef  scalar_t__ uint32_t ;
struct mem_input {int /*<<< orphan*/  request_address; int /*<<< orphan*/  current_address; } ;
struct dce_mem_input {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRPH_SURFACE_UPDATE_PENDING ; 
 int /*<<< orphan*/  GRPH_UPDATE ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct dce_mem_input* TO_DCE_MEM_INPUT (struct mem_input*) ; 

__attribute__((used)) static bool dce_mi_is_flip_pending(struct mem_input *mem_input)
{
	struct dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mem_input);
	uint32_t update_pending;

	REG_GET(GRPH_UPDATE, GRPH_SURFACE_UPDATE_PENDING, &update_pending);
	if (update_pending)
		return true;

	mem_input->current_address = mem_input->request_address;
	return false;
}