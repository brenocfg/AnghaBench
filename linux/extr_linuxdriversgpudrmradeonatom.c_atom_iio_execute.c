#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct radeon_device {int /*<<< orphan*/  family; } ;
struct atom_context {int io_attr; TYPE_2__* card; } ;
struct TYPE_6__ {int (* ioreg_read ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ioreg_write ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;TYPE_1__* dev; } ;
struct TYPE_5__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
#define  ATOM_IIO_CLEAR 136 
#define  ATOM_IIO_END 135 
#define  ATOM_IIO_MOVE_ATTR 134 
#define  ATOM_IIO_MOVE_DATA 133 
#define  ATOM_IIO_MOVE_INDEX 132 
#define  ATOM_IIO_NOP 131 
#define  ATOM_IIO_READ 130 
#define  ATOM_IIO_SET 129 
#define  ATOM_IIO_WRITE 128 
 int /*<<< orphan*/  CHIP_RV515 ; 
 int /*<<< orphan*/  CU16 (int) ; 
 int CU8 (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t atom_iio_execute(struct atom_context *ctx, int base,
				 uint32_t index, uint32_t data)
{
	struct radeon_device *rdev = ctx->card->dev->dev_private;
	uint32_t temp = 0xCDCDCDCD;

	while (1)
		switch (CU8(base)) {
		case ATOM_IIO_NOP:
			base++;
			break;
		case ATOM_IIO_READ:
			temp = ctx->card->ioreg_read(ctx->card, CU16(base + 1));
			base += 3;
			break;
		case ATOM_IIO_WRITE:
			if (rdev->family == CHIP_RV515)
				(void)ctx->card->ioreg_read(ctx->card, CU16(base + 1));
			ctx->card->ioreg_write(ctx->card, CU16(base + 1), temp);
			base += 3;
			break;
		case ATOM_IIO_CLEAR:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 2));
			base += 3;
			break;
		case ATOM_IIO_SET:
			temp |=
			    (0xFFFFFFFF >> (32 - CU8(base + 1))) << CU8(base +
									2);
			base += 3;
			break;
		case ATOM_IIO_MOVE_INDEX:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 3));
			temp |=
			    ((index >> CU8(base + 2)) &
			     (0xFFFFFFFF >> (32 - CU8(base + 1)))) << CU8(base +
									  3);
			base += 4;
			break;
		case ATOM_IIO_MOVE_DATA:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 3));
			temp |=
			    ((data >> CU8(base + 2)) &
			     (0xFFFFFFFF >> (32 - CU8(base + 1)))) << CU8(base +
									  3);
			base += 4;
			break;
		case ATOM_IIO_MOVE_ATTR:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 3));
			temp |=
			    ((ctx->
			      io_attr >> CU8(base + 2)) & (0xFFFFFFFF >> (32 -
									  CU8
									  (base
									   +
									   1))))
			    << CU8(base + 3);
			base += 4;
			break;
		case ATOM_IIO_END:
			return temp;
		default:
			pr_info("Unknown IIO opcode\n");
			return 0;
		}
}