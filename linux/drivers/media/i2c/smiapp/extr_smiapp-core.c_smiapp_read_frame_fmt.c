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
typedef  unsigned int u32 ;
struct smiapp_sensor {int visible_pixel_start; int embedded_end; int image_start; int /*<<< orphan*/  embedded_start; TYPE_1__* src; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SMIAPP_FRAME_FORMAT_DESC_2_PIXELCODE_MASK ; 
 unsigned int SMIAPP_FRAME_FORMAT_DESC_2_PIXELCODE_SHIFT ; 
 unsigned int SMIAPP_FRAME_FORMAT_DESC_2_PIXELS_MASK ; 
 unsigned int SMIAPP_FRAME_FORMAT_DESC_4_PIXELCODE_MASK ; 
 unsigned int SMIAPP_FRAME_FORMAT_DESC_4_PIXELCODE_SHIFT ; 
 unsigned int SMIAPP_FRAME_FORMAT_DESC_4_PIXELS_MASK ; 
#define  SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_BLACK 132 
#define  SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_DARK 131 
#define  SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_DUMMY 130 
#define  SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_EMBEDDED 129 
#define  SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_VISIBLE 128 
 unsigned int SMIAPP_FRAME_FORMAT_MODEL_SUBTYPE_NCOLS_MASK ; 
 unsigned int SMIAPP_FRAME_FORMAT_MODEL_SUBTYPE_NCOLS_SHIFT ; 
 unsigned int SMIAPP_FRAME_FORMAT_MODEL_SUBTYPE_NROWS_MASK ; 
 unsigned int SMIAPP_FRAME_FORMAT_MODEL_TYPE_2BYTE ; 
 unsigned int SMIAPP_FRAME_FORMAT_MODEL_TYPE_4BYTE ; 
 unsigned int SMIAPP_REG_U16_FRAME_FORMAT_DESCRIPTOR_2 (unsigned int) ; 
 unsigned int SMIAPP_REG_U32_FRAME_FORMAT_DESCRIPTOR_4 (unsigned int) ; 
 unsigned int SMIAPP_REG_U8_FRAME_FORMAT_MODEL_SUBTYPE ; 
 unsigned int SMIAPP_REG_U8_FRAME_FORMAT_MODEL_TYPE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int smiapp_read (struct smiapp_sensor*,unsigned int,unsigned int*) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smiapp_read_frame_fmt(struct smiapp_sensor *sensor)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	u32 fmt_model_type, fmt_model_subtype, ncol_desc, nrow_desc;
	unsigned int i;
	int pixel_count = 0;
	int line_count = 0;
	int rval;

	rval = smiapp_read(sensor, SMIAPP_REG_U8_FRAME_FORMAT_MODEL_TYPE,
			   &fmt_model_type);
	if (rval)
		return rval;

	rval = smiapp_read(sensor, SMIAPP_REG_U8_FRAME_FORMAT_MODEL_SUBTYPE,
			   &fmt_model_subtype);
	if (rval)
		return rval;

	ncol_desc = (fmt_model_subtype
		     & SMIAPP_FRAME_FORMAT_MODEL_SUBTYPE_NCOLS_MASK)
		>> SMIAPP_FRAME_FORMAT_MODEL_SUBTYPE_NCOLS_SHIFT;
	nrow_desc = fmt_model_subtype
		& SMIAPP_FRAME_FORMAT_MODEL_SUBTYPE_NROWS_MASK;

	dev_dbg(&client->dev, "format_model_type %s\n",
		fmt_model_type == SMIAPP_FRAME_FORMAT_MODEL_TYPE_2BYTE
		? "2 byte" :
		fmt_model_type == SMIAPP_FRAME_FORMAT_MODEL_TYPE_4BYTE
		? "4 byte" : "is simply bad");

	for (i = 0; i < ncol_desc + nrow_desc; i++) {
		u32 desc;
		u32 pixelcode;
		u32 pixels;
		char *which;
		char *what;
		u32 reg;

		if (fmt_model_type == SMIAPP_FRAME_FORMAT_MODEL_TYPE_2BYTE) {
			reg = SMIAPP_REG_U16_FRAME_FORMAT_DESCRIPTOR_2(i);
			rval = smiapp_read(sensor, reg,	&desc);
			if (rval)
				return rval;

			pixelcode =
				(desc
				 & SMIAPP_FRAME_FORMAT_DESC_2_PIXELCODE_MASK)
				>> SMIAPP_FRAME_FORMAT_DESC_2_PIXELCODE_SHIFT;
			pixels = desc & SMIAPP_FRAME_FORMAT_DESC_2_PIXELS_MASK;
		} else if (fmt_model_type
			   == SMIAPP_FRAME_FORMAT_MODEL_TYPE_4BYTE) {
			reg = SMIAPP_REG_U32_FRAME_FORMAT_DESCRIPTOR_4(i);
			rval = smiapp_read(sensor, reg, &desc);
			if (rval)
				return rval;

			pixelcode =
				(desc
				 & SMIAPP_FRAME_FORMAT_DESC_4_PIXELCODE_MASK)
				>> SMIAPP_FRAME_FORMAT_DESC_4_PIXELCODE_SHIFT;
			pixels = desc & SMIAPP_FRAME_FORMAT_DESC_4_PIXELS_MASK;
		} else {
			dev_dbg(&client->dev,
				"invalid frame format model type %d\n",
				fmt_model_type);
			return -EINVAL;
		}

		if (i < ncol_desc)
			which = "columns";
		else
			which = "rows";

		switch (pixelcode) {
		case SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_EMBEDDED:
			what = "embedded";
			break;
		case SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_DUMMY:
			what = "dummy";
			break;
		case SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_BLACK:
			what = "black";
			break;
		case SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_DARK:
			what = "dark";
			break;
		case SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_VISIBLE:
			what = "visible";
			break;
		default:
			what = "invalid";
			break;
		}

		dev_dbg(&client->dev,
			"0x%8.8x %s pixels: %d %s (pixelcode %u)\n", reg,
			what, pixels, which, pixelcode);

		if (i < ncol_desc) {
			if (pixelcode ==
			    SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_VISIBLE)
				sensor->visible_pixel_start = pixel_count;
			pixel_count += pixels;
			continue;
		}

		/* Handle row descriptors */
		switch (pixelcode) {
		case SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_EMBEDDED:
			if (sensor->embedded_end)
				break;
			sensor->embedded_start = line_count;
			sensor->embedded_end = line_count + pixels;
			break;
		case SMIAPP_FRAME_FORMAT_DESC_PIXELCODE_VISIBLE:
			sensor->image_start = line_count;
			break;
		}
		line_count += pixels;
	}

	if (sensor->embedded_end > sensor->image_start) {
		dev_dbg(&client->dev,
			"adjusting image start line to %u (was %u)\n",
			sensor->embedded_end, sensor->image_start);
		sensor->image_start = sensor->embedded_end;
	}

	dev_dbg(&client->dev, "embedded data from lines %d to %d\n",
		sensor->embedded_start, sensor->embedded_end);
	dev_dbg(&client->dev, "image data starts at line %d\n",
		sensor->image_start);

	return 0;
}