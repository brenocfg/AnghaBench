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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
#define  END_OF_SEQUENCE 129 
#define  LOAD_PAGE3 128 
 int USB_BUF_SZ ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  reg_w_page (struct gspca_dev*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void reg_w_var(struct gspca_dev *gspca_dev,
			const u8 *seq,
			const u8 *page3, unsigned int page3_len)
{
	int index, len;

	for (;;) {
		index = *seq++;
		len = *seq++;
		switch (len) {
		case END_OF_SEQUENCE:
			return;
		case LOAD_PAGE3:
			reg_w_page(gspca_dev, page3, page3_len);
			break;
		default:
			if (len > USB_BUF_SZ) {
				gspca_err(gspca_dev, "Incorrect variable sequence\n");
				return;
			}
			while (len > 0) {
				if (len < 8) {
					reg_w_buf(gspca_dev,
						index, seq, len);
					seq += len;
					break;
				}
				reg_w_buf(gspca_dev, index, seq, 8);
				seq += 8;
				index += 8;
				len -= 8;
			}
		}
	}
	/* not reached */
}