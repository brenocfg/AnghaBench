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
struct TYPE_2__ {int location; int /*<<< orphan*/  type; } ;
struct nvkm_outp {TYPE_1__ info; } ;
typedef  enum nvkm_ior_type { ____Placeholder_nvkm_ior_type } nvkm_ior_type ;
typedef  enum nvkm_ior_proto { ____Placeholder_nvkm_ior_proto } nvkm_ior_proto ;

/* Variables and functions */
 int CRT ; 
 int DAC ; 
#define  DCB_OUTPUT_ANALOG 132 
#define  DCB_OUTPUT_DP 131 
#define  DCB_OUTPUT_LVDS 130 
#define  DCB_OUTPUT_TMDS 129 
#define  DCB_OUTPUT_TV 128 
 int DP ; 
 int LVDS ; 
 int PIOR ; 
 int SOR ; 
 int TMDS ; 
 int TV ; 
 int UNKNOWN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static enum nvkm_ior_proto
nvkm_outp_xlat(struct nvkm_outp *outp, enum nvkm_ior_type *type)
{
	switch (outp->info.location) {
	case 0:
		switch (outp->info.type) {
		case DCB_OUTPUT_ANALOG: *type = DAC; return  CRT;
		case DCB_OUTPUT_TV    : *type = DAC; return   TV;
		case DCB_OUTPUT_TMDS  : *type = SOR; return TMDS;
		case DCB_OUTPUT_LVDS  : *type = SOR; return LVDS;
		case DCB_OUTPUT_DP    : *type = SOR; return   DP;
		default:
			break;
		}
		break;
	case 1:
		switch (outp->info.type) {
		case DCB_OUTPUT_TMDS: *type = PIOR; return TMDS;
		case DCB_OUTPUT_DP  : *type = PIOR; return TMDS; /* not a bug */
		default:
			break;
		}
		break;
	default:
		break;
	}
	WARN_ON(1);
	return UNKNOWN;
}