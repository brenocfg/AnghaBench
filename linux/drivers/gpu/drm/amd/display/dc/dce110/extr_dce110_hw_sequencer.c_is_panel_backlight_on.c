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
typedef  int uint32_t ;
struct dce_hwseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LVTMA_BLON ; 
 int /*<<< orphan*/  LVTMA_PWRSEQ_CNTL ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool is_panel_backlight_on(struct dce_hwseq *hws)
{
	uint32_t value;

	REG_GET(LVTMA_PWRSEQ_CNTL, LVTMA_BLON, &value);

	return value;
}