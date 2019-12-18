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
struct i2c_device {int features; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int FEATURE_I2C_BLOCK_READ ; 
 int FEATURE_SMBUS_PEC ; 
 int /*<<< orphan*/  I2C_FUNC_10BIT_ADDR ; 
 int I2C_FUNC_I2C ; 
 int /*<<< orphan*/  I2C_FUNC_PROTOCOL_MANGLING ; 
 int I2C_FUNC_SMBUS_BLOCK_DATA ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BLOCK_PROC_CALL ; 
 int I2C_FUNC_SMBUS_BYTE ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_EMUL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int I2C_FUNC_SMBUS_PEC ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_PROC_CALL ; 
 int I2C_FUNC_SMBUS_QUICK ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_BLOCK_DATA ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_BYTE ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_READ_I2C_BLOCK ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_WORD_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WRITE_BLOCK_DATA ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WRITE_BYTE ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WRITE_I2C_BLOCK ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WRITE_WORD_DATA ; 
 struct i2c_device* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static u32 i801_func(struct i2c_adapter *adapter)
{
	struct i2c_device *priv = i2c_get_adapdata(adapter);

	/* original settings
	 * u32 f = I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	 * I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	 * I2C_FUNC_SMBUS_BLOCK_DATA | I2C_FUNC_SMBUS_WRITE_I2C_BLOCK |
	 * ((priv->features & FEATURE_SMBUS_PEC) ? I2C_FUNC_SMBUS_PEC : 0) |
	 * ((priv->features & FEATURE_I2C_BLOCK_READ) ?
	 * I2C_FUNC_SMBUS_READ_I2C_BLOCK : 0);
	 */

	// http://lxr.free-electrons.com/source/include/uapi/linux/i2c.h#L85

	u32 f =
		I2C_FUNC_I2C                     | /* 0x00000001 (I enabled this one) */
		!I2C_FUNC_10BIT_ADDR             | /* 0x00000002 */
		!I2C_FUNC_PROTOCOL_MANGLING      | /* 0x00000004 */
		((priv->features & FEATURE_SMBUS_PEC) ? I2C_FUNC_SMBUS_PEC : 0) | /* 0x00000008 */
		!I2C_FUNC_SMBUS_BLOCK_PROC_CALL  | /* 0x00008000 */
		I2C_FUNC_SMBUS_QUICK             | /* 0x00010000 */
		!I2C_FUNC_SMBUS_READ_BYTE        | /* 0x00020000 */
		!I2C_FUNC_SMBUS_WRITE_BYTE       | /* 0x00040000 */
		!I2C_FUNC_SMBUS_READ_BYTE_DATA   | /* 0x00080000 */
		!I2C_FUNC_SMBUS_WRITE_BYTE_DATA  | /* 0x00100000 */
		!I2C_FUNC_SMBUS_READ_WORD_DATA   | /* 0x00200000 */
		!I2C_FUNC_SMBUS_WRITE_WORD_DATA  | /* 0x00400000 */
		!I2C_FUNC_SMBUS_PROC_CALL        | /* 0x00800000 */
		!I2C_FUNC_SMBUS_READ_BLOCK_DATA  | /* 0x01000000 */
		!I2C_FUNC_SMBUS_WRITE_BLOCK_DATA | /* 0x02000000 */
		((priv->features & FEATURE_I2C_BLOCK_READ) ? I2C_FUNC_SMBUS_READ_I2C_BLOCK : 0) | /* 0x04000000 */
		I2C_FUNC_SMBUS_WRITE_I2C_BLOCK   | /* 0x08000000 */

		I2C_FUNC_SMBUS_BYTE              | /* _READ_BYTE  _WRITE_BYTE */
		I2C_FUNC_SMBUS_BYTE_DATA         | /* _READ_BYTE_DATA  _WRITE_BYTE_DATA */
		I2C_FUNC_SMBUS_WORD_DATA         | /* _READ_WORD_DATA  _WRITE_WORD_DATA */
		I2C_FUNC_SMBUS_BLOCK_DATA        | /* _READ_BLOCK_DATA  _WRITE_BLOCK_DATA */
		!I2C_FUNC_SMBUS_I2C_BLOCK        | /* _READ_I2C_BLOCK  _WRITE_I2C_BLOCK */
		!I2C_FUNC_SMBUS_EMUL;              /* _QUICK  _BYTE  _BYTE_DATA  _WORD_DATA  _PROC_CALL  _WRITE_BLOCK_DATA  _I2C_BLOCK _PEC */
	return f;
}