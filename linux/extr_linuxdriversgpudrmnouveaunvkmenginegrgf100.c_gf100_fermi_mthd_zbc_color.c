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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int /*<<< orphan*/  engine; } ;
struct gf100_gr {int dummy; } ;
struct fermi_a_zbc_color_v0 {int format; int index; int /*<<< orphan*/  l2; int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
#define  FERMI_A_ZBC_COLOR_V0_FMT_A2B10G10R10 146 
#define  FERMI_A_ZBC_COLOR_V0_FMT_A2R10G10B10 145 
#define  FERMI_A_ZBC_COLOR_V0_FMT_A8B8G8R8 144 
#define  FERMI_A_ZBC_COLOR_V0_FMT_A8BL8GL8RL8 143 
#define  FERMI_A_ZBC_COLOR_V0_FMT_A8R8G8B8 142 
#define  FERMI_A_ZBC_COLOR_V0_FMT_A8RL8GL8BL8 141 
#define  FERMI_A_ZBC_COLOR_V0_FMT_AN8BN8GN8RN8 140 
#define  FERMI_A_ZBC_COLOR_V0_FMT_AS8BS8GS8RS8 139 
#define  FERMI_A_ZBC_COLOR_V0_FMT_AU2BU10GU10RU10 138 
#define  FERMI_A_ZBC_COLOR_V0_FMT_AU8BU8GU8RU8 137 
#define  FERMI_A_ZBC_COLOR_V0_FMT_BF10GF11RF11 136 
#define  FERMI_A_ZBC_COLOR_V0_FMT_R16_G16_B16_A16 135 
#define  FERMI_A_ZBC_COLOR_V0_FMT_RF16_GF16_BF16_AF16 134 
#define  FERMI_A_ZBC_COLOR_V0_FMT_RF32_GF32_BF32_AF32 133 
#define  FERMI_A_ZBC_COLOR_V0_FMT_RN16_GN16_BN16_AN16 132 
#define  FERMI_A_ZBC_COLOR_V0_FMT_RS16_GS16_BS16_AS16 131 
#define  FERMI_A_ZBC_COLOR_V0_FMT_RU16_GU16_BU16_AU16 130 
#define  FERMI_A_ZBC_COLOR_V0_FMT_UNORM_ONE 129 
#define  FERMI_A_ZBC_COLOR_V0_FMT_ZERO 128 
 struct gf100_gr* gf100_gr (int /*<<< orphan*/ ) ; 
 int gf100_gr_zbc_color_get (struct gf100_gr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct fermi_a_zbc_color_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_gr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gf100_fermi_mthd_zbc_color(struct nvkm_object *object, void *data, u32 size)
{
	struct gf100_gr *gr = gf100_gr(nvkm_gr(object->engine));
	union {
		struct fermi_a_zbc_color_v0 v0;
	} *args = data;
	int ret = -ENOSYS;

	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, false))) {
		switch (args->v0.format) {
		case FERMI_A_ZBC_COLOR_V0_FMT_ZERO:
		case FERMI_A_ZBC_COLOR_V0_FMT_UNORM_ONE:
		case FERMI_A_ZBC_COLOR_V0_FMT_RF32_GF32_BF32_AF32:
		case FERMI_A_ZBC_COLOR_V0_FMT_R16_G16_B16_A16:
		case FERMI_A_ZBC_COLOR_V0_FMT_RN16_GN16_BN16_AN16:
		case FERMI_A_ZBC_COLOR_V0_FMT_RS16_GS16_BS16_AS16:
		case FERMI_A_ZBC_COLOR_V0_FMT_RU16_GU16_BU16_AU16:
		case FERMI_A_ZBC_COLOR_V0_FMT_RF16_GF16_BF16_AF16:
		case FERMI_A_ZBC_COLOR_V0_FMT_A8R8G8B8:
		case FERMI_A_ZBC_COLOR_V0_FMT_A8RL8GL8BL8:
		case FERMI_A_ZBC_COLOR_V0_FMT_A2B10G10R10:
		case FERMI_A_ZBC_COLOR_V0_FMT_AU2BU10GU10RU10:
		case FERMI_A_ZBC_COLOR_V0_FMT_A8B8G8R8:
		case FERMI_A_ZBC_COLOR_V0_FMT_A8BL8GL8RL8:
		case FERMI_A_ZBC_COLOR_V0_FMT_AN8BN8GN8RN8:
		case FERMI_A_ZBC_COLOR_V0_FMT_AS8BS8GS8RS8:
		case FERMI_A_ZBC_COLOR_V0_FMT_AU8BU8GU8RU8:
		case FERMI_A_ZBC_COLOR_V0_FMT_A2R10G10B10:
		case FERMI_A_ZBC_COLOR_V0_FMT_BF10GF11RF11:
			ret = gf100_gr_zbc_color_get(gr, args->v0.format,
							   args->v0.ds,
							   args->v0.l2);
			if (ret >= 0) {
				args->v0.index = ret;
				return 0;
			}
			break;
		default:
			return -EINVAL;
		}
	}

	return ret;
}