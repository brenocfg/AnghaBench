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
typedef  unsigned int u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct regmap {int dummy; } ;
struct mt9v032 {int /*<<< orphan*/  vratio; int /*<<< orphan*/  hratio; struct regmap* regmap; struct v4l2_rect crop; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9V032_CHIP_CONTROL ; 
 unsigned int MT9V032_CHIP_CONTROL_DOUT_ENABLE ; 
 unsigned int MT9V032_CHIP_CONTROL_SEQUENTIAL ; 
 int /*<<< orphan*/  MT9V032_COLUMN_START ; 
 int /*<<< orphan*/  MT9V032_READ_MODE ; 
 unsigned int MT9V032_READ_MODE_COLUMN_BIN_SHIFT ; 
 unsigned int const MT9V032_READ_MODE_RESERVED ; 
 unsigned int MT9V032_READ_MODE_ROW_BIN_SHIFT ; 
 int /*<<< orphan*/  MT9V032_ROW_START ; 
 int /*<<< orphan*/  MT9V032_WINDOW_HEIGHT ; 
 int /*<<< orphan*/  MT9V032_WINDOW_WIDTH ; 
 int fls (int /*<<< orphan*/ ) ; 
 int mt9v032_update_hblank (struct mt9v032*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,unsigned int const,unsigned int const) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mt9v032* to_mt9v032 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v032_s_stream(struct v4l2_subdev *subdev, int enable)
{
	const u16 mode = MT9V032_CHIP_CONTROL_DOUT_ENABLE
		       | MT9V032_CHIP_CONTROL_SEQUENTIAL;
	struct mt9v032 *mt9v032 = to_mt9v032(subdev);
	struct v4l2_rect *crop = &mt9v032->crop;
	struct regmap *map = mt9v032->regmap;
	unsigned int hbin;
	unsigned int vbin;
	int ret;

	if (!enable)
		return regmap_update_bits(map, MT9V032_CHIP_CONTROL, mode, 0);

	/* Configure the window size and row/column bin */
	hbin = fls(mt9v032->hratio) - 1;
	vbin = fls(mt9v032->vratio) - 1;
	ret = regmap_update_bits(map, MT9V032_READ_MODE,
				 ~MT9V032_READ_MODE_RESERVED,
				 hbin << MT9V032_READ_MODE_COLUMN_BIN_SHIFT |
				 vbin << MT9V032_READ_MODE_ROW_BIN_SHIFT);
	if (ret < 0)
		return ret;

	ret = regmap_write(map, MT9V032_COLUMN_START, crop->left);
	if (ret < 0)
		return ret;

	ret = regmap_write(map, MT9V032_ROW_START, crop->top);
	if (ret < 0)
		return ret;

	ret = regmap_write(map, MT9V032_WINDOW_WIDTH, crop->width);
	if (ret < 0)
		return ret;

	ret = regmap_write(map, MT9V032_WINDOW_HEIGHT, crop->height);
	if (ret < 0)
		return ret;

	ret = mt9v032_update_hblank(mt9v032);
	if (ret < 0)
		return ret;

	/* Switch to master "normal" mode */
	return regmap_update_bits(map, MT9V032_CHIP_CONTROL, mode, mode);
}