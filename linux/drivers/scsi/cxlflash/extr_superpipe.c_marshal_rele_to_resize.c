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
struct dk_cxlflash_resize {int /*<<< orphan*/  rsrc_handle; int /*<<< orphan*/  context_id; int /*<<< orphan*/  hdr; } ;
struct dk_cxlflash_release {int /*<<< orphan*/  rsrc_handle; int /*<<< orphan*/  context_id; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */

__attribute__((used)) static void marshal_rele_to_resize(struct dk_cxlflash_release *release,
				   struct dk_cxlflash_resize *resize)
{
	resize->hdr = release->hdr;
	resize->context_id = release->context_id;
	resize->rsrc_handle = release->rsrc_handle;
}