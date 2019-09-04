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
struct radeon_device {int dummy; } ;
struct radeon_cs_parser {int cs_flags; scalar_t__ ring; int /*<<< orphan*/  ib; scalar_t__ parser_error; int /*<<< orphan*/ * chunk_ib; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ERESTARTSYS ; 
 scalar_t__ R600_RING_TYPE_UVD_INDEX ; 
 int RADEON_CS_USE_VM ; 
 scalar_t__ TN_RING_TYPE_VCE1_INDEX ; 
 scalar_t__ TN_RING_TYPE_VCE2_INDEX ; 
 int radeon_cs_parse (struct radeon_device*,scalar_t__,struct radeon_cs_parser*) ; 
 int radeon_cs_sync_rings (struct radeon_cs_parser*) ; 
 int radeon_ib_schedule (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_uvd_note_usage (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_vce_note_usage (struct radeon_device*) ; 

__attribute__((used)) static int radeon_cs_ib_chunk(struct radeon_device *rdev,
			      struct radeon_cs_parser *parser)
{
	int r;

	if (parser->chunk_ib == NULL)
		return 0;

	if (parser->cs_flags & RADEON_CS_USE_VM)
		return 0;

	r = radeon_cs_parse(rdev, parser->ring, parser);
	if (r || parser->parser_error) {
		DRM_ERROR("Invalid command stream !\n");
		return r;
	}

	r = radeon_cs_sync_rings(parser);
	if (r) {
		if (r != -ERESTARTSYS)
			DRM_ERROR("Failed to sync rings: %i\n", r);
		return r;
	}

	if (parser->ring == R600_RING_TYPE_UVD_INDEX)
		radeon_uvd_note_usage(rdev);
	else if ((parser->ring == TN_RING_TYPE_VCE1_INDEX) ||
		 (parser->ring == TN_RING_TYPE_VCE2_INDEX))
		radeon_vce_note_usage(rdev);

	r = radeon_ib_schedule(rdev, &parser->ib, NULL, true);
	if (r) {
		DRM_ERROR("Failed to schedule IB !\n");
	}
	return r;
}