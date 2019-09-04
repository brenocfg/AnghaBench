#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct radeon_mode_info {TYPE_1__* atom_context; } ;
struct radeon_device {struct radeon_mode_info mode_info; } ;
struct radeon_atom_ss {int /*<<< orphan*/  refdiv; int /*<<< orphan*/  range; int /*<<< orphan*/  delay; int /*<<< orphan*/  step; int /*<<< orphan*/  type; int /*<<< orphan*/  percentage; } ;
struct _ATOM_SPREAD_SPECTRUM_INFO {int /*<<< orphan*/ * asSS_Info; } ;
struct _ATOM_SPREAD_SPECTRUM_ASSIGNMENT {int ucSS_Id; int /*<<< orphan*/  ucRecommendedRef_Div; int /*<<< orphan*/  ucSS_Range; int /*<<< orphan*/  ucSS_Delay; int /*<<< orphan*/  ucSS_Step; int /*<<< orphan*/  ucSpreadSpectrumType; int /*<<< orphan*/  usSpreadSpectrumPercentage; } ;
struct TYPE_2__ {int bios; } ;
typedef  int /*<<< orphan*/  ATOM_SPREAD_SPECTRUM_ASSIGNMENT ;
typedef  int /*<<< orphan*/  ATOM_COMMON_TABLE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPLL_SS_Info ; 
 scalar_t__ atom_parse_data_header (TYPE_1__*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct radeon_atom_ss*,int /*<<< orphan*/ ,int) ; 

bool radeon_atombios_get_ppll_ss_info(struct radeon_device *rdev,
				      struct radeon_atom_ss *ss,
				      int id)
{
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, PPLL_SS_Info);
	uint16_t data_offset, size;
	struct _ATOM_SPREAD_SPECTRUM_INFO *ss_info;
	struct _ATOM_SPREAD_SPECTRUM_ASSIGNMENT *ss_assign;
	uint8_t frev, crev;
	int i, num_indices;

	memset(ss, 0, sizeof(struct radeon_atom_ss));
	if (atom_parse_data_header(mode_info->atom_context, index, &size,
				   &frev, &crev, &data_offset)) {
		ss_info =
			(struct _ATOM_SPREAD_SPECTRUM_INFO *)(mode_info->atom_context->bios + data_offset);

		num_indices = (size - sizeof(ATOM_COMMON_TABLE_HEADER)) /
			sizeof(ATOM_SPREAD_SPECTRUM_ASSIGNMENT);
		ss_assign = (struct _ATOM_SPREAD_SPECTRUM_ASSIGNMENT*)
			((u8 *)&ss_info->asSS_Info[0]);
		for (i = 0; i < num_indices; i++) {
			if (ss_assign->ucSS_Id == id) {
				ss->percentage =
					le16_to_cpu(ss_assign->usSpreadSpectrumPercentage);
				ss->type = ss_assign->ucSpreadSpectrumType;
				ss->step = ss_assign->ucSS_Step;
				ss->delay = ss_assign->ucSS_Delay;
				ss->range = ss_assign->ucSS_Range;
				ss->refdiv = ss_assign->ucRecommendedRef_Div;
				return true;
			}
			ss_assign = (struct _ATOM_SPREAD_SPECTRUM_ASSIGNMENT*)
				((u8 *)ss_assign + sizeof(struct _ATOM_SPREAD_SPECTRUM_ASSIGNMENT));
		}
	}
	return false;
}