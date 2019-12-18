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
typedef  scalar_t__ u8 ;
struct intel_sdvo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDVO_CMD_GET_HBUF_INFO ; 
 int /*<<< orphan*/  intel_sdvo_get_value (struct intel_sdvo*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static bool intel_sdvo_get_hbuf_size(struct intel_sdvo *intel_sdvo,
				     u8 *hbuf_size)
{
	if (!intel_sdvo_get_value(intel_sdvo, SDVO_CMD_GET_HBUF_INFO,
				  hbuf_size, 1))
		return false;

	/* Buffer size is 0 based, hooray! However zero means zero. */
	if (*hbuf_size)
		(*hbuf_size)++;

	return true;
}