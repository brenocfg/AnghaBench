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
typedef  int u8 ;
typedef  int u16 ;
struct sd {size_t sensor; } ;
struct gspca_dev {int dummy; } ;
struct additional_sensor_data {int const* n3; int const* n4; int n4sz; int reg80; int reg8e; int const* data5; int const* nset8; int const* stream; int /*<<< orphan*/  data3; int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  D_STREAM ; 
 int EINVAL ; 
 int EIO ; 
 size_t SENSOR_LT168G ; 
 size_t SENSOR_OM6802 ; 
 size_t SENSOR_OTHER ; 
 size_t SENSOR_TAS5130A ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int reg_r (struct gspca_dev*,int const) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int const*,int) ; 
 int /*<<< orphan*/  reg_w_ixbuf (struct gspca_dev*,int,int /*<<< orphan*/ ,int) ; 
 struct additional_sensor_data* sensor_data ; 
 int const* sensor_reset ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	/* some of this registers are not really needed, because
	 * they are overridden by setbrigthness, setcontrast, etc.,
	 * but won't hurt anyway, and can help someone with similar webcam
	 * to see the initial parameters.*/
	struct sd *sd = (struct sd *) gspca_dev;
	const struct additional_sensor_data *sensor;
	int i;
	u16 sensor_id;
	u8 test_byte = 0;

	static const u8 read_indexs[] =
		{ 0x0a, 0x0b, 0x66, 0x80, 0x81, 0x8e, 0x8f, 0xa5,
		  0xa6, 0xa8, 0xbb, 0xbc, 0xc6, 0x00 };
	static const u8 n1[] =
			{0x08, 0x03, 0x09, 0x03, 0x12, 0x04};
	static const u8 n2[] =
			{0x08, 0x00};

	sensor_id = (reg_r(gspca_dev, 0x06) << 8)
			| reg_r(gspca_dev, 0x07);
	switch (sensor_id & 0xff0f) {
	case 0x0801:
		gspca_dbg(gspca_dev, D_PROBE, "sensor tas5130a\n");
		sd->sensor = SENSOR_TAS5130A;
		break;
	case 0x0802:
		gspca_dbg(gspca_dev, D_PROBE, "sensor lt168g\n");
		sd->sensor = SENSOR_LT168G;
		break;
	case 0x0803:
		gspca_dbg(gspca_dev, D_PROBE, "sensor 'other'\n");
		sd->sensor = SENSOR_OTHER;
		break;
	case 0x0807:
		gspca_dbg(gspca_dev, D_PROBE, "sensor om6802\n");
		sd->sensor = SENSOR_OM6802;
		break;
	default:
		pr_err("unknown sensor %04x\n", sensor_id);
		return -EINVAL;
	}

	if (sd->sensor == SENSOR_OM6802) {
		reg_w_buf(gspca_dev, n1, sizeof n1);
		i = 5;
		while (--i >= 0) {
			reg_w_buf(gspca_dev, sensor_reset, sizeof sensor_reset);
			test_byte = reg_r(gspca_dev, 0x0063);
			msleep(100);
			if (test_byte == 0x17)
				break;		/* OK */
		}
		if (i < 0) {
			pr_err("Bad sensor reset %02x\n", test_byte);
			return -EIO;
		}
		reg_w_buf(gspca_dev, n2, sizeof n2);
	}

	i = 0;
	while (read_indexs[i] != 0x00) {
		test_byte = reg_r(gspca_dev, read_indexs[i]);
		gspca_dbg(gspca_dev, D_STREAM, "Reg 0x%02x = 0x%02x\n",
			  read_indexs[i], test_byte);
		i++;
	}

	sensor = &sensor_data[sd->sensor];
	reg_w_buf(gspca_dev, sensor->n3, sizeof sensor->n3);
	reg_w_buf(gspca_dev, sensor->n4, sensor->n4sz);

	if (sd->sensor == SENSOR_LT168G) {
		test_byte = reg_r(gspca_dev, 0x80);
		gspca_dbg(gspca_dev, D_STREAM, "Reg 0x%02x = 0x%02x\n", 0x80,
			  test_byte);
		reg_w(gspca_dev, 0x6c80);
	}

	reg_w_ixbuf(gspca_dev, 0xd0, sensor->data1, sizeof sensor->data1);
	reg_w_ixbuf(gspca_dev, 0xc7, sensor->data2, sizeof sensor->data2);
	reg_w_ixbuf(gspca_dev, 0xe0, sensor->data3, sizeof sensor->data3);

	reg_w(gspca_dev, (sensor->reg80 << 8) + 0x80);
	reg_w(gspca_dev, (sensor->reg80 << 8) + 0x80);
	reg_w(gspca_dev, (sensor->reg8e << 8) + 0x8e);
	reg_w(gspca_dev, (0x20 << 8) + 0x87);
	reg_w(gspca_dev, (0x20 << 8) + 0x88);
	reg_w(gspca_dev, (0x20 << 8) + 0x89);

	reg_w_buf(gspca_dev, sensor->data5, sizeof sensor->data5);
	reg_w_buf(gspca_dev, sensor->nset8, sizeof sensor->nset8);
	reg_w_buf(gspca_dev, sensor->stream, sizeof sensor->stream);

	if (sd->sensor == SENSOR_LT168G) {
		test_byte = reg_r(gspca_dev, 0x80);
		gspca_dbg(gspca_dev, D_STREAM, "Reg 0x%02x = 0x%02x\n", 0x80,
			  test_byte);
		reg_w(gspca_dev, 0x6c80);
	}

	reg_w_ixbuf(gspca_dev, 0xd0, sensor->data1, sizeof sensor->data1);
	reg_w_ixbuf(gspca_dev, 0xc7, sensor->data2, sizeof sensor->data2);
	reg_w_ixbuf(gspca_dev, 0xe0, sensor->data3, sizeof sensor->data3);

	return 0;
}