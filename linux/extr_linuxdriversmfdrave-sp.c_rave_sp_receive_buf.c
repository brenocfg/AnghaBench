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
struct device {int dummy; } ;
struct serdev_device {struct device dev; } ;
struct rave_sp_deframer {int state; unsigned char* data; int length; } ;
struct rave_sp {struct rave_sp_deframer deframer; } ;

/* Variables and functions */
#define  RAVE_SP_DLE 133 
#define  RAVE_SP_ETX 132 
#define  RAVE_SP_EXPECT_DATA 131 
#define  RAVE_SP_EXPECT_ESCAPED_DATA 130 
#define  RAVE_SP_EXPECT_SOF 129 
#define  RAVE_SP_STX 128 
 struct rave_sp* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  rave_sp_receive_frame (struct rave_sp*,unsigned char*,int) ; 

__attribute__((used)) static int rave_sp_receive_buf(struct serdev_device *serdev,
			       const unsigned char *buf, size_t size)
{
	struct device *dev = &serdev->dev;
	struct rave_sp *sp = dev_get_drvdata(dev);
	struct rave_sp_deframer *deframer = &sp->deframer;
	const unsigned char *src = buf;
	const unsigned char *end = buf + size;

	while (src < end) {
		const unsigned char byte = *src++;

		switch (deframer->state) {
		case RAVE_SP_EXPECT_SOF:
			if (byte == RAVE_SP_STX)
				deframer->state = RAVE_SP_EXPECT_DATA;
			break;

		case RAVE_SP_EXPECT_DATA:
			/*
			 * Treat special byte values first
			 */
			switch (byte) {
			case RAVE_SP_ETX:
				rave_sp_receive_frame(sp,
						      deframer->data,
						      deframer->length);
				/*
				 * Once we extracted a complete frame
				 * out of a stream, we call it done
				 * and proceed to bailing out while
				 * resetting the framer to initial
				 * state, regardless if we've consumed
				 * all of the stream or not.
				 */
				goto reset_framer;
			case RAVE_SP_STX:
				dev_warn(dev, "Bad frame: STX before ETX\n");
				/*
				 * If we encounter second "start of
				 * the frame" marker before seeing
				 * corresponding "end of frame", we
				 * reset the framer and ignore both:
				 * frame started by first SOF and
				 * frame started by current SOF.
				 *
				 * NOTE: The above means that only the
				 * frame started by third SOF, sent
				 * after this one will have a chance
				 * to get throught.
				 */
				goto reset_framer;
			case RAVE_SP_DLE:
				deframer->state = RAVE_SP_EXPECT_ESCAPED_DATA;
				/*
				 * If we encounter escape sequence we
				 * need to skip it and collect the
				 * byte that follows. We do it by
				 * forcing the next iteration of the
				 * encompassing while loop.
				 */
				continue;
			}
			/*
			 * For the rest of the bytes, that are not
			 * speical snoflakes, we do the same thing
			 * that we do to escaped data - collect it in
			 * deframer buffer
			 */

			/* FALLTHROUGH */

		case RAVE_SP_EXPECT_ESCAPED_DATA:
			if (deframer->length == sizeof(deframer->data)) {
				dev_warn(dev, "Bad frame: Too long\n");
				/*
				 * If the amount of data we've
				 * accumulated for current frame so
				 * far starts to exceed the capacity
				 * of deframer's buffer, there's
				 * nothing else we can do but to
				 * discard that data and start
				 * assemblying a new frame again
				 */
				goto reset_framer;
			}

			deframer->data[deframer->length++] = byte;

			/*
			 * We've extracted out special byte, now we
			 * can go back to regular data collecting
			 */
			deframer->state = RAVE_SP_EXPECT_DATA;
			break;
		}
	}

	/*
	 * The only way to get out of the above loop and end up here
	 * is throught consuming all of the supplied data, so here we
	 * report that we processed it all.
	 */
	return size;

reset_framer:
	/*
	 * NOTE: A number of codepaths that will drop us here will do
	 * so before consuming all 'size' bytes of the data passed by
	 * serdev layer. We rely on the fact that serdev layer will
	 * re-execute this handler with the remainder of the Rx bytes
	 * once we report actual number of bytes that we processed.
	 */
	deframer->state  = RAVE_SP_EXPECT_SOF;
	deframer->length = 0;

	return src - buf;
}