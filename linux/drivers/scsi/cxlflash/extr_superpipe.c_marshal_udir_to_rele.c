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
struct dk_cxlflash_udirect {int /*<<< orphan*/  rsrc_handle; int /*<<< orphan*/  context_id; int /*<<< orphan*/  hdr; } ;
struct dk_cxlflash_release {int /*<<< orphan*/  rsrc_handle; int /*<<< orphan*/  context_id; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */

__attribute__((used)) static void marshal_udir_to_rele(struct dk_cxlflash_udirect *udirect,
				 struct dk_cxlflash_release *release)
{
	release->hdr = udirect->hdr;
	release->context_id = udirect->context_id;
	release->rsrc_handle = udirect->rsrc_handle;
}