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
typedef  int u32 ;
typedef  int u16 ;
struct fb_info {int dummy; } ;
struct fb_image {unsigned char* data; int width; } ;

/* Variables and functions */
 int GDC_CMD_BITMAP ; 
 int GDC_CMD_BODY_BACK_COLOR ; 
 int GDC_CMD_BODY_FORE_COLOR ; 
 int GDC_REG_MODE_BITMAP ; 
 int GDC_ROP_COPY ; 
 int GDC_TYPE_DRAWBITMAPP ; 
 int GDC_TYPE_SETCOLORREGISTER ; 
 int GDC_TYPE_SETREGISTER ; 
 int cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char const*,int) ; 

__attribute__((used)) static void mb86290fb_imageblit1(u32 *cmd, u16 step, u16 dx, u16 dy,
				 u16 width, u16 height, u32 fgcolor,
				 u32 bgcolor, const struct fb_image *image,
				 struct fb_info *info)
{
	int i;
	unsigned const char *line;
	u16 bytes;

	/* set colors and raster operation regs */
	cmd[0] = (GDC_TYPE_SETREGISTER << 24) | (1 << 16) | GDC_REG_MODE_BITMAP;
	/* Set raster operation */
	cmd[1] = (2 << 7) | (GDC_ROP_COPY << 9);
	cmd[2] =
	    (GDC_TYPE_SETCOLORREGISTER << 24) | (GDC_CMD_BODY_FORE_COLOR << 16);
	cmd[3] = fgcolor;
	cmd[4] =
	    (GDC_TYPE_SETCOLORREGISTER << 24) | (GDC_CMD_BODY_BACK_COLOR << 16);
	cmd[5] = bgcolor;

	i = 0;
	line = image->data;
	bytes = (image->width + 7) >> 3;

	/* and the image */
	cmd[6] = (GDC_TYPE_DRAWBITMAPP << 24) |
	    (GDC_CMD_BITMAP << 16) | (2 + (step * height));
	cmd[7] = (dy << 16) | dx;
	cmd[8] = (height << 16) | width;

	while (i < height) {
		memcpy(&cmd[9 + i * step], line, step << 2);
#ifdef __LITTLE_ENDIAN
		{
			int k = 0;
			for (k = 0; k < step; k++)
				cmd[9 + i * step + k] =
				    cpu_to_be32(cmd[9 + i * step + k]);
		}
#endif
		line += bytes;
		i++;
	}
}