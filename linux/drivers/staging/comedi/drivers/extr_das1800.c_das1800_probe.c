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
typedef  struct das1800_board {unsigned char id; int /*<<< orphan*/  name; } const das1800_board ;
struct comedi_device {int /*<<< orphan*/  class_dev; int /*<<< orphan*/  board_name; struct das1800_board const* board_ptr; scalar_t__ iobase; } ;

/* Variables and functions */
 size_t BOARD_DAS1801AO ; 
 size_t BOARD_DAS1801HC ; 
 size_t BOARD_DAS1801ST ; 
 size_t BOARD_DAS1801ST_DA ; 
 size_t BOARD_DAS1802HR ; 
 size_t BOARD_DAS1802HR_DA ; 
 scalar_t__ DAS1800_DIGITAL ; 
#define  DAS1800_ID_AO 133 
#define  DAS1800_ID_HC 132 
#define  DAS1800_ID_HR 131 
#define  DAS1800_ID_HR_DA 130 
#define  DAS1800_ID_ST 129 
#define  DAS1800_ID_ST_DA 128 
 int ENODEV ; 
 struct das1800_board const* das1800_boards ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned char,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned char,int /*<<< orphan*/ ) ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static int das1800_probe(struct comedi_device *dev)
{
	const struct das1800_board *board = dev->board_ptr;
	unsigned char id;

	id = (inb(dev->iobase + DAS1800_DIGITAL) >> 4) & 0xf;

	/*
	 * The dev->board_ptr will be set by comedi_device_attach() if the
	 * board name provided by the user matches a board->name in this
	 * driver. If so, this function sanity checks the id to verify that
	 * the board is correct.
	 */
	if (board) {
		if (board->id == id)
			return 0;
		dev_err(dev->class_dev,
			"probed id does not match board id (0x%x != 0x%x)\n",
			id, board->id);
		return -ENODEV;
	}

	 /*
	  * If the dev->board_ptr is not set, the user is trying to attach
	  * an unspecified board to this driver. In this case the id is used
	  * to 'probe' for the dev->board_ptr.
	  */
	switch (id) {
	case DAS1800_ID_ST_DA:
		/* das-1701st-da, das-1702st-da, das-1801st-da, das-1802st-da */
		board = &das1800_boards[BOARD_DAS1801ST_DA];
		break;
	case DAS1800_ID_HR_DA:
		/* das-1702hr-da, das-1802hr-da */
		board = &das1800_boards[BOARD_DAS1802HR_DA];
		break;
	case DAS1800_ID_AO:
		/* das-1701ao, das-1702ao, das-1801ao, das-1802ao */
		board = &das1800_boards[BOARD_DAS1801AO];
		break;
	case DAS1800_ID_HR:
		/*  das-1702hr, das-1802hr */
		board = &das1800_boards[BOARD_DAS1802HR];
		break;
	case DAS1800_ID_ST:
		/* das-1701st, das-1702st, das-1801st, das-1802st */
		board = &das1800_boards[BOARD_DAS1801ST];
		break;
	case DAS1800_ID_HC:
		/* das-1801hc, das-1802hc */
		board = &das1800_boards[BOARD_DAS1801HC];
		break;
	default:
		dev_err(dev->class_dev, "invalid probe id 0x%x\n", id);
		return -ENODEV;
	}
	dev->board_ptr = board;
	dev->board_name = board->name;
	dev_warn(dev->class_dev,
		 "probed id 0x%0x: %s series (not recommended)\n",
		 id, board->name);
	return 0;
}