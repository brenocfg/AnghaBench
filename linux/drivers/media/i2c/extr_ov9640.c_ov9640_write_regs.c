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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ov9640_reg_alt {int /*<<< orphan*/  com15; int /*<<< orphan*/  com13; int /*<<< orphan*/  com12; int /*<<< orphan*/  com7; } ;
struct ov9640_reg {int reg; int /*<<< orphan*/  val; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct ov9640_reg*) ; 
 int EINVAL ; 
 int MEDIA_BUS_FMT_UYVY8_2X8 ; 
#define  OV9640_COM12 138 
#define  OV9640_COM13 137 
#define  OV9640_COM15 136 
#define  OV9640_COM7 135 
#define  W_CIF 134 
#define  W_QCIF 133 
#define  W_QQCIF 132 
#define  W_QQVGA 131 
#define  W_QVGA 130 
#define  W_SXGA 129 
#define  W_VGA 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ov9640_reg_write (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 struct ov9640_reg* ov9640_regs_cif ; 
 struct ov9640_reg* ov9640_regs_qcif ; 
 struct ov9640_reg* ov9640_regs_qqcif ; 
 struct ov9640_reg* ov9640_regs_qqvga ; 
 struct ov9640_reg* ov9640_regs_qvga ; 
 struct ov9640_reg* ov9640_regs_rgb ; 
 struct ov9640_reg* ov9640_regs_sxga ; 
 struct ov9640_reg* ov9640_regs_vga ; 
 struct ov9640_reg* ov9640_regs_yuv ; 

__attribute__((used)) static int ov9640_write_regs(struct i2c_client *client, u32 width,
		u32 code, struct ov9640_reg_alt *alts)
{
	const struct ov9640_reg	*ov9640_regs, *matrix_regs;
	unsigned int		ov9640_regs_len, matrix_regs_len;
	unsigned int		i;
	int			ret;
	u8			val;

	/* select register configuration for given resolution */
	switch (width) {
	case W_QQCIF:
		ov9640_regs	= ov9640_regs_qqcif;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_qqcif);
		break;
	case W_QQVGA:
		ov9640_regs	= ov9640_regs_qqvga;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_qqvga);
		break;
	case W_QCIF:
		ov9640_regs	= ov9640_regs_qcif;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_qcif);
		break;
	case W_QVGA:
		ov9640_regs	= ov9640_regs_qvga;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_qvga);
		break;
	case W_CIF:
		ov9640_regs	= ov9640_regs_cif;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_cif);
		break;
	case W_VGA:
		ov9640_regs	= ov9640_regs_vga;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_vga);
		break;
	case W_SXGA:
		ov9640_regs	= ov9640_regs_sxga;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_sxga);
		break;
	default:
		dev_err(&client->dev, "Failed to select resolution!\n");
		return -EINVAL;
	}

	/* select color matrix configuration for given color encoding */
	if (code == MEDIA_BUS_FMT_UYVY8_2X8) {
		matrix_regs	= ov9640_regs_yuv;
		matrix_regs_len	= ARRAY_SIZE(ov9640_regs_yuv);
	} else {
		matrix_regs	= ov9640_regs_rgb;
		matrix_regs_len	= ARRAY_SIZE(ov9640_regs_rgb);
	}

	/* write register settings into the module */
	for (i = 0; i < ov9640_regs_len; i++) {
		val = ov9640_regs[i].val;

		switch (ov9640_regs[i].reg) {
		case OV9640_COM7:
			val |= alts->com7;
			break;
		case OV9640_COM12:
			val |= alts->com12;
			break;
		case OV9640_COM13:
			val |= alts->com13;
			break;
		case OV9640_COM15:
			val |= alts->com15;
			break;
		}

		ret = ov9640_reg_write(client, ov9640_regs[i].reg, val);
		if (ret)
			return ret;
	}

	/* write color matrix configuration into the module */
	for (i = 0; i < matrix_regs_len; i++) {
		ret = ov9640_reg_write(client, matrix_regs[i].reg,
				       matrix_regs[i].val);
		if (ret)
			return ret;
	}

	return 0;
}